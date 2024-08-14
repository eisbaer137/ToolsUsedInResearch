# ToolsUsedInResearch
data structure programming using CPP, SF networks generation

Examples of data structure: binary search tree, hash table, graph structure with BFS(Breadth First Search) and DFS(Depth First Search). They are basically c++ rewritten versions of c programming language based data structure that I made long time ago when I was a undergraduate student.

generation of SF network(graph) code was made when I was a graduate student after learning C++ programming language. it can generate random scale free sample networks whose degree distribution follows ~K^-d(d: dimension). At the time, a python module, networkX was not able to generate sample networks whose minimum degree is larger than or equal to 2. So, I made it myself using C++ programming language.

This demo is built using Visual Studio Code on Debian 10 linux.

Test system: intel core i3-6300 with nVidia GeForce GTX 1050ti

Here goes the sample DAG structure used in this demo.

![DAG_computation](https://github.com/user-attachments/assets/589d4f1e-40a0-41b2-a1f1-cb0bf0d5392f)

Computations done at each node are completely independent and don’t write on the same memory block, which lead me not to use measures for avoiding race condition such as mutex objects.

