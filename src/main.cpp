#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void server(chrono::system_clock::time_point &serverTime) {
  while (true) {
    serverTime = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(serverTime);
    cout << "Tiempo del servidor: \t\t" << ctime(&t) << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
}

void client(chrono::system_clock::time_point &serverTime) {
  while (true) {
    chrono::system_clock::time_point requestTime = chrono::system_clock::now();
    this_thread::sleep_for(chrono::seconds(3));

    chrono::system_clock::time_point receiveTime = chrono::system_clock::now();
    chrono::duration<double> latency = (receiveTime - requestTime) / 2;

    chrono::system_clock::time_point adjustedTime =
        serverTime +
        chrono::duration_cast<chrono::system_clock::duration>(latency);
    time_t t = chrono::system_clock::to_time_t(adjustedTime);
    cout << "Tiempo aj del cliente: \t\t" << ctime(&t) << endl;
  }
}

int main() {
  chrono::system_clock::time_point serverTime;

  thread serverThread(server, ref(serverTime));
  thread clientThread(client, ref(serverTime));
  serverThread.join();
  clientThread.join();

  return 0;
}
