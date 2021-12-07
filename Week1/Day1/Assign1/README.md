# Hello, World!

This is a simple hello-world project (with a twist) that you can easily run and execute using Docker!
You will require docker to run and execute the Dockerfile.

Use "./build.sh" to automatically build the Dockerfile, generate a new container, and attach to that container.

Inside the Docker container, use 'make' to automatically compile the source code and generate an executable object file.

## Step 1: Build the Dockerfile
Run the build script to automatically handle generating an image, creating a container, and attaching to that container.

## Step 2: Run the command 'make'
Run the 'make' command to build the application

## Step 3: Run the object file
Use the command ./hello-brute-force.o to run the application. Careful not to touch it while it's thinking (it won't break the program, just make the output look funny).

## Step 4: Use the 'exit' Command to Detach from the Container
After detaching, you may want to run the killall script to kill all running containers (don't run this if you have containers you want to keep open!)
