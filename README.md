*This project has been created as part of the 42 curriculum by lyokoiga*
<br><br/>
<h1 align="center">💻Codexion</h1>
<p align="center"><i>"Hello, World<b>(s)</b>!"</i></p>

## 📌 Description

**Codexion** is a project that aims to mimic the Dining Philosopher's Problem.

In this project, there's a room of coders who must compile a certain number of times, and each of them owns a dongle. They can only compile using 2 dongles, needing to borrow the dongle on their neighbor coder.

The coders are sitting in a circular pattern, meaning N coder will have N dongle on their left and N + 1 dongle on their right, except for the last coder, who will have N dongle and index 0 dongle.

The project tackles issues with concurrency and multithreading, requiring us to create a thread for each coder to work with when compiling, and a thread for the Monitor, who is sort of a supervisor of sorts. They will be the one to tell which coders can compile, when dongles are ready, when someone has reached burnout, etc...

Each coder must run a loop of Compile -> Debug -> Refactor before finishing to compile once. And if they run out of time? They burn out, and the program ends.

Once every coder has successfully compiled a certain number of times dictated by the input, the program ends.

I eventually created a way to check if a simuation, given the inputs, would be impossible to run, exiting the program instead of continuing to run it.

## ⌨️ Instructions

To use the program, first you must compile it using ``make``

I added a couple other ``make`` instructions:

- ``make``: compiles the program normally
- ``make re``: recompiles the program
- ``make clean``: deletes every .o file for clarity
- ``make fclean``: deletes every .o file and the program file itself
- ``make reclean``: recompiles the program and cleans every .o file

After compiling, run the program in the terminal by typing `./codexion` followed by 8 inputs in the following order:

|input|value|
|------|------|
|max_coders|The number of coders around the table|
|time_to_burnout|The amount of time (in ms) coders are allowed before they burnout|
|time_to_compile|The amount of time (in ms) coders will take to compile|
|time_to_debug|The amount of time (in ms) coders will take to debug|
|time_to_refactor|The amount of time (in ms) coders will take to refactor|
|total_compiles|The total number of full compiles each coder must complete before the program can end|
|cooldown_time|The amount of time it takes for a dongle to recharge after a coder uses it|
|scheduler|The policy which the scheduler will use in order to organize the heap. Can only be FIFO or EDF|

Example: ```./codexion 6 1500 400 100 100 5 100 edf```

FIFO stands for "First in First out" and EDF stands for "Earliest Deadline First".

The program will exit and handle gracefully any invalid inputs. Namely negative numbers or zeroes, strings where numbers are required and typos in scheduler.

## ⛓️‍💥 Blocking Cases Handled

My program prevents deadlock by having every coder require both dongles available to be grabbed in order to grab them.

The coder struct I used, contains two pointers to the dongles they own. One for their left dongle and one for their right dongle. At the start of the coder's loop, they send a request to a heap and wait for a signal from the monitor. This breaks Coffman's "Hold and Wait" condition by requiring that a coder obtains BOTH of their required resources before being able to proceed. This also coincidentally breaks Coffman's "Circular Wait" condition, since if no coder can hog the dongles, they won't keep waiting on resources they need from other coders.

The monitor will check the whole heap for any requests that can be fulfilled. If a request cannot be fulfilled, it will send that request to the queue and reorganize the heap in order to be able to check every request possible. When a request is fulfilled, the monitor reserves that coder's dongles, sets their can_compile variable to 1 and signals for them to move on.

The way the scheduler works to prevent starvation as much as possible is that when a coder sends a request to the heap, it will organize the heap according to the current policy chosen, and the scheduler will check if the root of the heap (the request with highest priority) is fulfillable. If it isn't, it'll send it to a queue and reorganize the heap, bubbling up the next request with most priority. It will repeat this process until the heap is empty, and then it will send every request from the queue back into the heap.

Cooldown handling was done by initializing the last_cooldown_timestamp of each dongle to negative the input's cooldown_time. The monitor will check if the current timestamp - the dongle's cooldown timestamp is greater than the cooldown sent to the input. And after a coder uses each dongle, they will use elapsed_time(sim->start_time) to grab the elapsed time from when the simulation first started.

Finally, the scheduler can detect when a coder has burned out before the 10ms time limit, when checking for new requests, if the heap is empty, it will wait for 5ms on a pthread_cond_timedwait before going back to the simulation loop, sleeping for 1ms and then restarting the loop (checking burnout -> checking completion -> checking requests). It will always be able to detect burnout within the allowed 10ms.

A print_mutex is located inside the simulation struct, and is shared across every coder and the monitor thread itself, ensuring that at no point two prints will overlap with eachother. Some may come before others given the way I decided to handle printing itself, but none of them will overlap, which is the important part.

## 💾 Thread Synchronization Mechanisms

I used a lot of mutexes and conds to synchronize the threads. A start_cond pthread_cond to have every coder start off at the same time and wait for the simulation to finish initializing, rather than immediately on creation.

I prevent requests from being overwritten by other coders by locking the scheduler's mutex before sending a request, same thing for most other things the coders or the monitor will touch, such as the print, the state machine for when the simulation ends for whatever reason, or the dongles for when coders update their cooldown start timestamp.

At first I was using a "is_ready" variable on top of the "in_use" variable, which the coder and the scheduler would manipulate by themselves, which created issues surrounding the coders being able to grab the dongles before they were ready. I fixed this by removing the is_ready variable and having only the scheduler control whether or not a dongle was ready, meanwhile the coder would only control if the dongle was in use and the timestamp of when they let it go.

## Resources

https://www.geeksforgeeks.org/c/thread-functions-in-c-c/
https://www.geeksforgeeks.org/linux-unix/mutex-lock-for-linux-thread-synchronization/
https://www.ibm.com/docs/en/aix/7.2.0?topic=programming-terminating-threads
https://faq.computersciencewiki.org/index.php/home/article/coffman-conditions

### 🤖 AI Usage

AI was used to:
- Help with handling dongle data racing
- Help with understanding binary heaps and debugging heap-traversal
- Help with finding the best cleanup ordering
- Help with fixing threads stalling
- Help with the feasibility formula
- Help with organizing this README and finding typos

At no point in this entire project did I ask AI to create code for me to copy without understanding it first.