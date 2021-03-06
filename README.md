# Mini-UPS
DUKE-ECE568-FINAL
# ERSS-project-xh114-xl346

#### Step

- ##### Install packages

  ```shell
  sudo apt-get install gcc g++ make valgrind #For C development
  sudo apt-get install emacs screen #For editing
  sudo apt-get install postgresql #Database
  sudo apt-get install python python3-pip #For Django
  sudo pip3 install django psycopg2
  sudo apt-get libssl-dev libxerces-c-dev libpqxx-dev #Libaries
  ```

  For protobuf,  follow the instruction on https://github.com/protocolbuffers/protobuf

- ##### Create database ups_db (first time)

  Type `sudo -u postgres psql` . Create a database named "ups_db" : `CREATE DATABASE ups_db`

- ##### Run world simulator

  ```shell
  cd world_simulator_exec-master/docker_deploy
  sudo docker-compose build #first time
  sudo docker-compose up
  ```

- ##### Run ups backend

   ```shell
   cd backend_fortest
   # for <option>
   # 0: make and run program.
   # 1: rebuild program
   # 2: rebuild libprotocpl.a and then rebuild program
   ./run.sh <world_simulator_host> <amazon_host> <option> 
   ```

   You can check log files that show the server's interaction with world simulator, amazon and frontend.

- ##### Run ups frontend

  ```shell
  cd frontend/upssite
  python3 manage.py migrate #first time
  #remember to add your vm address to ALLOWED_HOSTS in setting.py
  python3 manage.py runserver 0.0.0.0:8000 
  ```

  Visit the website in local machine with url "<vm_addr>:8000/ups/home". 

  You can use commands in test/database_test/testsql  to check the functionality of the frontend.

- ##### Simple test

   ```shell
   cd testing
   ./test.sh <world_simulator_host> <ups_host> <option> 
   ```

- ##### Test with Mini-Amazon

#### Our Grade: 98/100

Avg = 96.2, Median = 98
