# matchmaking

### Description

This is the task that had to be completed in order to receive a scholarship at Central University.

You can see the task [here](TASK.md)

### How to run

Run server and solution with `docker-compose -f "docker-compose.yml" up --build --abort-on-container-exit`

You can locally separately run the [server](matchmaking/server) 
```
pip install -r requirements.txt && 
    python3 server.py
```

and the [solution](matchmaking/solution)
```
mkdir -p build && cd build &&
    cmake .. -DBUILD_LOCAL=ON &&
    cmake --build . &&
    ./Solution
```

use `ctest` in build directory to run tests 
