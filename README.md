# LedControl test task
Test task: Create led server which will talk with clients via named pipes. 
Detail description is in embedded-cpp-test.pdf.
Project consists of 2 part: server side(c++) and client side(bash script).

Build steps via vagrant:
1. Download [virtual box](https://www.virtualbox.org/wiki/Downloads "virtual box").
2. Download [vagrant](https://www.vagrantup.com/downloads.html "vagrant").
3. Run **vagrant up** and wait about 5 minutes.
4. Project is in **/vagrant**.
5. Server is in **/vagrant/server**. Name is **ledServer**.
6. Client will be found in** /vagrant** with name **client.sh**.