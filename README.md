# SebBinLoader
A simple but useful loader for SafeExamBrowser´s seb_x64 for reverse-engineering purposes.

### Why did I create this?
In order to emulate seb_x64.dll I had to make an effective loader which allowed me to place breakpoints and inline hooks without the need of launching SafeExamBrowser each time.
Although I have stripped this version of all hooks and modifications made to seb_x64, it is very useful if you ever decide to reverse engineer it (IDA + x64dbg + ret-sync).

### Which versions does it support?
I'd assume it works on every SEB version which has seb_x64, iirc the exports stay the same and the signing certificate they use has not changed as of (2025-10-03) so the logic should be similar if not exactly the same.

### How am I supposed to debug seb_x64 if some parts are obfuscated and virtualized?
I'm not going to give any instructions on how to remove all obfuscation and virtualization, but it is rather simple if you combine IDA + x64dbg + Python. 
I wish you the best luck.
