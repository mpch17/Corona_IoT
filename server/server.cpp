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
json read_data();

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

        if (connection.error)
        {
            std::cerr << connection.error_msg << std::endl << std::endl;
            continue;
        }

        std::thread client_thread([&connection]() { handle_client(connection); });
    }
}

// Handles client.
// Clients that haven't send anything in TIME2DEATH seconds are removed.
void handle_client(const conn& client)
{
    using namespace std::chrono;

    corona::node n = corona::INV_NODE;
    std::string msg = "";
    auto timer = std::chrono::high_resolution_clock::now();
    bool kill = false;
    std::thread reader([&msg, &kill, &client]() {
        while (!kill)   // kill does not necessarily kill this thread. If kill = false and client disconnects, then conn_read() will block forever.
        {
            char* buffer = new char[100];
            conn_read(client, buffer, 100);

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
        }

        if (kill)   // Reading thread should be killed, but we'll let it block for now.
        {
            if (!(n == corona::INV_NODE))
            {
                std_graph.remove_node(n);
                max_flow_graph = corona::parse_frame(std_graph);
            }

            break;
        }

        else
        {
            handle_message(client, msg);
            json2node(n, msg);
            msg = "";
        }
    }
}

// Attempts to parse JSON string into node instance.
void json2node(corona::node& n, const std::string str)
{

}

// Either saves or incoming message or responds with saved data depending on client type.
// If IoT node, save data received. If it's from the app, send the latest saved data.
void handle_message(const conn& client, const std::string message)
{
    json jstr = json::parse(message.c_str());

    if (std::string(jstr["req_type"]).compare("POST") == 0)
        store_data(jstr);

    else
    {
        std::string json_str = read_data().dump();
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
json read_data()
{
    // TODO: Compute path.
    // TODO: Remember to use mutex lock.
    // TODO: Return not only flow path, but also all data in std_graph so app can see number of people in each room.
}
