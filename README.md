PC Server Project:

This project is based on socet programming. The PC as a server and the phone as a client. Both(server and client) must be connected to the same network.

This video demonstrates the objective of this project: https://drive.google.com/file/d/1vr96KlBGwkeetA6PqOk1Pt-NrWwaO61C/view?usp=sharing

Steps:

  1- Write code for the server (PC): code are demonstrated in code folder. 

  2- Download application for the client (phone):
     
  ![Mobile Application](https://i.postimg.cc/XvyQCdTm/Whats-App-Image-2023-09-28-at-2-58-19-PM.jpg)
      

  
  3- Select "Create Client"

  
  ![Client](https://i.postimg.cc/13Yyt1QM/Screenshot-20231001-194145-Tcp-Udp-Server-Client.jpg).

  
  4- Write The IP and port corresponding to your PC and choose the TCP mode.

  
  ![Configuration](https://i.postimg.cc/gjMTDd4T/Screenshot-20231001-194149-Tcp-Udp-Server-Client.jpg).

  
  
  5- Open the created client and write commands to be sent or you can configure specific buttons as follow:

  - Click on the "+" button:
  
  ![Buttons](https://i.postimg.cc/7Y8VF5Jn/Screenshot-20231001-194226-Tcp-Udp-Server-Client.jpg).

  
  - Start configure your buttons by set label and value to be sent to your server once you click on the created button.
  
  ![Buttons](https://i.postimg.cc/c4SRDPPD/Screenshot-20231001-194233-Tcp-Udp-Server-Client.jpg).
  

  6- Use an appropriate mechanism to execute received commnads.
  - In my code I have used fork() and excelp().
    
  - fork()   : The Fork system call is used for creating a new process in Linux, and Unix systems, which is called the child process, which runs concurrently with the process that makes the fork() call (parent process). After a new child process is created, both processes will execute the next instruction following the fork() system call.
    fork Return:
                Negative Value: The creation of a child process was unsuccessful.
                Zero: Returned to the newly created child process.
                Positive value: Returned to parent or caller. The value contains the process ID of the newly created child process.
   
  - excelp() : It creates a new process image, fork creates a new child process which is ececuting the same code then excelp converts this process to another image. The new image represent the execution of the sent command: "browser" -> open firefox.

  ![Buttons](https://i.postimg.cc/RVx0wB20/Screenshot-from-2023-10-01-20-09-22.png).


  Here we used fork() to create a new process, and pid used to stroe the return value. The pid value will equal zero in the new process and will equal some number for the parent process. 
  We used the if condition (pid == 0 ) to insure that we are in the child process this line helped me to avoid executing excelp in the parent process, which will terminate the server and for sure we don't want that.

Refrences:
1- https://www.geeksforgeeks.org/fork-system-call/
2- https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_lib_ref/e/execlp.html
3- https://www.geeksforgeeks.org/socket-programming-cc/
4- https://marketsplash.com/tutorials/cpp/cplusplus-scoket/
