#include <communicate.h>
#include <thread>
#include <mutex>
#include <map>
#include <iostream>
#include <string>
#include <chrono>
#include <ratio>
#include <ctime>
#include <nlohmann/json.hpp>
#include "IO/frame.hpp"
#include "graph/flow_graph.hpp"
#include "config.hpp"

#define TIME2DEATH 60
#define PORT 48677

using json = nlohmann::json;

// Prototypes.
void clients_listen(const conn& server);
void handle_client(const conn& client);
void json2node(corona::node& n, const std::string str);
void handle_message(const conn& client, const std::string message);
void store_data(const json& j);
json read_data(const int& source, const int& sink);
std::vector<std::pair<unsigned long, unsigned short>> node_values();
std::pair<unsigned long, unsigned long> read_source_sink(const std::string& str);

// Graphs.
corona::frame std_graph;
corona::flow_graph max_flow_graph;

std::mutex graph_mtx;

int main()
{
    conn server = endpoint_init(NULL, PORT, SERVER);

    std::thread client_listener([&]() { clients_listen(server); });
    client_listener.join();

    return 0;
}

// Listens for client.
// Runs forever, so run this is a separate thread.
void clients_listen(const conn& server)
{
    while (true)
    {
        conn connection = conn_listen(server);

#if LOG
        std::cout << "Client connected." << std::endl;
#endif

        if (connection.error)
        {
#if LOG
            std::cerr << connection.error_msg << std::endl << std::endl;
#endif
            continue;
        }

        std::thread client_thread([&connection]() { handle_client(connection); });
        client_thread.join();
    }
}

// Handles client.
// Clients that haven't send anything in TIME2DEATH seconds are removed.
void handle_client(const conn& client)
{
    using namespace std::chrono;

    corona::node n = corona::invalid_node_t();
    std::string msg = "";
    auto timer = high_resolution_clock::now();
    bool kill = false;
    std::thread reader([&msg, &kill, &client]() {
        while (!kill)   // kill does not necessarily kill this thread. If kill = false and client disconnects, then conn_read() will block forever.
        {
            char* buffer = new char[1000];
            conn_read(client, buffer, 1000);

            while (!msg.empty());
            msg = buffer;
            delete[] buffer;
        }
    });

    while (true)
    {
        while (msg.empty() && !kill)
        {
            duration<double> elapsed_time = duration_cast<duration<double>>(high_resolution_clock::now() - timer);

            if (elapsed_time.count() >= TIME2DEATH)
                kill = true;

            timer = high_resolution_clock::now();
        }

        if (kill)   // Reading thread should be killed, but we'll let it block for now.
        {
            if (!(n == corona::node(corona::invalid_node_t())))
            {
                std_graph.remove_node(n);
                max_flow_graph = corona::parse_frame(std_graph);
            }

            break;
        }

        else
        {
            handle_message(client, msg);
            msg = "";
        }
    }
}

// Attempts to parse JSON string into node instance.
void json2node(corona::node& n, const std::string str)
{
    json j = json::parse(str.c_str());
    n = corona::node((bool) j["is_hallway"], (float) j["longitude"], (float) j["latitude"],
                    (unsigned long) j["id"], (int) j["index"], (unsigned long) j["edge1"],
                    (unsigned long) j["edge2"], (unsigned short) j["people_count"]);
}

// Either saves or incoming message or responds with saved data depending on client type.
// If IoT node, save data received. If it's from the app, send the latest saved data.
void handle_message(const conn& client, const std::string message)
{
#if LOG
    std::cout << "Message: " << message << std::endl;
#endif

    json jstr = json::parse(message.c_str());

    if (std::string(jstr["req_type"]).compare("POST") == 0)
        store_data(jstr);

    else
    {
        std::pair<unsigned long, unsigned long> ss = read_source_sink(message);
        std::string json_str = read_data(0, 0).dump();
        conn_write(client, json_str.c_str(), json_str.size());
    }
}

// Stores information in graph.
void store_data(const json& j)
{
    corona::node n((bool) j["is_hallway"], (float) j["longitude"], (float) j["latitude"],
            (unsigned long) j["id"], (int) j["id"], (unsigned long) j["edge1"],
            (unsigned long) j["edge2"], (unsigned short) j["people_count"]);

    graph_mtx.lock();

    if (n.get_people_count() > ROOM_THRESHOLD)
        std_graph.remove_node(n);

    else
        std_graph.add_node(n);

    max_flow_graph = corona::parse_frame(std_graph);
    graph_mtx.unlock();
}

// Reads data.
// Data is maximum flow path result.
json read_data(const int& source, const int& sink)
{
    graph_mtx.lock();
    max_flow_graph.compute_path(source, sink);

    json j;
    j["max_flow"] = max_flow_graph.get_flow().second;
    j["path"] = max_flow_graph.get_flow().first;
    j["node_values"] = node_values();

    graph_mtx.unlock();
    return j;
}

// Returns std::vector of pairs, where key is node ID and value is people count.
std::vector<std::pair<unsigned long, unsigned short>> node_values()
{
    std::vector<std::pair<unsigned long, unsigned short>> values;
    std::vector<corona::node> nodes = std_graph.get_nodes();

    for (corona::node n : nodes)
    {
        values.push_back(std::pair<unsigned long, unsigned short>(n.get_id(), n.get_people_count()));
    }

    return values;
}

// Retreives HTTP headers for source and sink in graph.
// Key and value are both 0 if argument is unpassable.
std::pair<unsigned long, unsigned long> read_source_sink(const std::string& str)
{
    std::pair<unsigned long, unsigned long> ss;
    std::size_t source_pos = str.find("edge1");
    std::size_t sink_pos = str.find("edge2");

    if (source_pos == std::string::npos || sink_pos == std::string::npos)
        return std::pair<unsigned long, unsigned long>(0, 0);

    ss.first = stoul(str.substr(source_pos + 2, str.find_first_of("\r", source_pos + 2) - (source_pos + 2)));
    ss.second = stoul(str.substr(sink_pos + 2, str.find_first_of("\r", sink_pos + 2) - (sink_pos + 2)));

    return ss;
}
