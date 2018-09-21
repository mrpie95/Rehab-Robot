<h1>CppCMS Server</h1>

<h2>Server</h2>
<p>CppCMS i used to create a web server that is run in C++.  This web server acts as the interface between the tablet and the other modules such as simon says and the story telling modules</p>



<h2>Server</h2>
<p>The server class is in charge of hosting the site responding and recieving infomation from the tablet. </p>

<h2>Logger</h2>
A logging class has been created in order to keep track of what is going wrong and to help in diagnsis of bugs. Current just including the logger.h, instating an object and callig x.LogEvent(string) will log the the time and whatever you specify. Currently not fininshed but does do basic logs.

<h3>To be added</h3>
<ul>
<li>Type of log</li>
<li>Singleton design</li>
<li>Options</li>
</ul>


<h2>Server</h2>
<p>Currently there is no CMake file so compilation is done manually. Running the server requires the specification of a a config file (config.js). </p>

<h3>Build</h3>
<pre><code>
 c++ server.cpp logger.cpp -lcppcms -o server
</code></pre>

<h3>Run</h3>
<pre><code>
 ./server -c config.js
</code></pre>



