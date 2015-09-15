Simple Database Challenge
===

This repo is based on the "Simple Database Challenge" on thumbtack.com. 

But by now the page of this problem is down for some reasons. So there is one pdf format replica from google snapshot in this repo to show you the background and requirements of this challenge.

It takes me about 90+ minutes to finish this task. As I'm using C++ as the programming language and writing code with a mechanical keyboard with Cherry green switch that prones to the tired fingers. I think it's not a bad grade for that. (I'm also drunk!)

## Functionality Analysis

This simple DB supports "SET", "UNSET", "GET", "NUMEQUALTO" commands, and also supports transactions that you can undo all the commands before you send the "COMMIT".

## Performance Analysis

The crux of this project is to quickly build a prototype of a simplified DB. And of course, not focus on the performance. So there is only some example test cases to prove the correctness of my codes. 

Run “do_test.py” for test result. You can also add your own test cases to the directory “cases”.

Here is the time complexity for all kinds of commands:

* BEGIN - O(1)
* GET   - O(1)
* SET   - O(1)
* UNSET - O(1)
* NUMEQUALTO - O(1)
* COMMIT - O(k)
* ROLLBACK - O(k)

Here `k` is the number of commands between `BEGIN` and `COMMIT` or `BEGIN` and `ROLLBACK`.

