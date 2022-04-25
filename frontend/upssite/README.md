# ERSS-project-xh114-xl346

#### Step
0. ##### Required Libraries to install
   #### Install Google Protobuf

   Follow the instruction on https://github.com/protocolbuffers/protobuf

   #### Compile Protocol Buffers

   Follow the instruction on https://developers.google.com/protocol-buffers/docs/cpptutorial

   ```shell
   protoc -I=protocolfiles --cpp_out=protocolcodes protocolfiles/world_ups.proto
   ```
1. ##### Run world simulator

   ```shell
   cd world_simulator_exec-master/docker_deploy
   sudo docker-compose build #first time
   sudo docker-compose up
   ```

2. ##### Run amazon server

   ```shell
   cd testing
   # for <option>
   # 0: make and run program.
   # 1: rebuild program
   # 2: rebuild libprotocpl.a and then rebuild program
   ./test.sh <world_simulator_host> <ups_host> <option> 
   ```

3. ##### Run frontend(can skip this step)

   ```shell
   cd frontend/upssite/
   python3 manage.py makemigrations #first time
   python3 manage.py migrate #first time
   python3 manage.py run 0.0.0.0:8000
   ```

   Visit the website in local machine with url "<vm_addr>:8000/ups"

4. ##### Run ups server

   ```shell
   cd backend_fortest
   ./run.sh <world_simulator_host> <amazon_host> <option> 
   ```

   





#### Team Document

https://docs.google.com/document/d/1NiRAtG57TfeZvTNMx9N9HidYSrP1IM8-qrJZ_WFRLDI/edit#
