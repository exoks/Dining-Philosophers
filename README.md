<div align="center">
  <img src="https://github.com/user-attachments/assets/fa633d2f-052f-4786-a78a-15dbc62e5324" width="900" />
</div>

This project introduces fundamental concepts of **multithreading**, **synchronization** and concurrency, It simulates the famous ***dining philosophers problem***, which explores **resource allocation**, **deadlocks**, and **race conditions** in concurrent programming.

### **Project Goal :** ### 
The goal of the project is to implement a simulation where a group of philosophers alternates between three states: `Thinking`, `Eating` and `Sleeping`, Each philosopher must acquire ***two forks*** (shared resources) to eat, ensuring proper synchronization to prevent ***deadlocks*** and ***starvation***.

### **Getting starged :** ###
This repository contains two versions of the Dining Philosophers problem, each using different methods for handling concurrency:
  * **philo_thrd**: Uses threads and **mutexes** for synchronization.
  * **philo_ps**: Uses processes and **semaphores** for synchronization.

Both versions simulate the philosophers' behavior while solving problems like deadlocks, race conditions, and resource allocation. This project is a practical way to learn about multithreading, multiprocessing, and synchronization in programming.

### **Usage :** ###
1. Clone the repository
```sh
git clone git@github.com:exoks/Dining-Philosophers.git
cd Dining-Philosophers 
```
2. Compile the project:
```sh
make
```
  * This will generate the `philo` executable.

#### **Running the Program :** ####

```sh
./philo
```
***Running the program will display a CLI Usage Menu :***
<div>
  <img width="1000" alt="Image" src="https://github.com/user-attachments/assets/a9ae86cf-d087-4d5a-a2f3-be6d0c303632"/>
</div>

> **NOTE**  
> - The usage menu provides detailed instructions on how to use the `philo` program.

#### **Example :** ####
<div align="center">
    <img src="https://github.com/user-attachments/assets/dafa483b-0eaf-4c13-9c03-6d7a3869065d">
</div>

### **CleanUp :** ###
* Remove object files:
```sh
make clean
```

* Remove all binaries and object files:
```sh
make fclean
```

---
