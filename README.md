granasatClient
========================================================================
![GranaSAT](https://cloud.githubusercontent.com/assets/3924815/3865957/261cbb64-1fb6-11e4-8724-823485676743.jpg)
========================================================================
Client side of GranaSAT experiment, selected for BEXUS 19 campaign.  
This code was originally written by Mario Román (`@M42`) and Alejandro García (`@agarciamontoro`) and released under a **GPLv2** license. The server side code can be seen in its [GitHub page](https://github.com/agarciamontoro/granasatServer).

## Usage
### Building
The main executable and the auxiliar executable `imageTransform` are built by executing 
`make` in the main directoy. The doxygen documentation is built using `make doc`:
``` bash
make all
make doc
```

### Execution
The **client** can be executed directly using `./granasatClient`.
However, it is recommended to run the script `./client.sh`, which saves the
simplified execution log into a new file and displays the image window.  
The execution log can be used to retrieve the data that was read from the raspberry server.

### Connection
The **client** will try to contact the server in the IP direction `SERVER_IP` provided
in `client.h`. Three sockets will be used to read data and send commands to the server.  
The server side execution can be started after or before the client execution, and the client
will try to recover the connection if it were cut. Anyway, the client can be used without connection,
and the changed parameters are sent to the server when the connection is restored.

## Do you want to know more about GranaSAT?
See more information at [GranaSAT website](http://granasat.ugr.es).  
Like our fanpage at [Facebook](http://www.facebook.com/granasat).  
Follow us on Twitter: [@granaSAT](http://twitter.com/GranaSAT).  
