<h1 align="center"> Philosophers | <picture> <source media="(prefers-color-scheme: dark)" srcset="https://cdn.simpleicons.org/42/white"> <img alt="42" width=40 align="center" src="https://cdn.simpleicons.org/42/Black"> </picture> Cursus </h1>
A project to simulate the classic Dining Philosophers problem using C threads and mutexes.

<br>
<br>


<img align="right" width="150" src="https://github.com/Abdullah-Alawad/imgs/blob/main/100_Success.png">
About the Project
This project is a multithreaded simulation of philosophers sitting around a table, where each philosopher eats, sleeps, and thinks while competing for shared resources — the forks. The goal is to avoid deadlocks, data races, and ensure no philosopher dies due to starvation.

<h3>🛠️ Instructions</h3>

<ul>
  <li>In <bold>philo</bold> folder, you can find the Makefile and code to run.</li>
  <li>Use the provided <code>Makefile</code> to compile all source files. It should not relink unnecessarily.</li>
  <li>Used the following libraries and functions: <code>pthread</code>, <code>mutex</code>, <code>gettimeofday</code>, <code>usleep</code>.</li>
</ul>

<pre><code>&gt; make
&gt; ./philo &lt;number_of_philosophers&gt; &lt;time_to_die&gt; &lt;time_to_eat&gt; &lt;time_to_sleep&gt; [number_of_times_each_philosopher_must_eat]
</code></pre>

<blockquote>
  <p><strong>⚠️ WARNING:</strong><br>
  All time values are in <strong>milliseconds</strong>.<br>
  The final argument is <em>optional</em>: if provided, the simulation ends once all philosophers have eaten that many times.</p>
</blockquote>

<h3>📜 Simulation Rules</h3>

<ul>
  <li>Each philosopher has a unique number from <code>1</code> to <code>number_of_philosophers</code>.</li>
  <li>Each philosopher must take the <strong>left and right forks</strong> to eat.</li>
  <li>If there is only <strong>one philosopher</strong>, they will never eat and will die.</li>
  <li>After <strong>eating</strong>, philosophers will <strong>sleep</strong>, then <strong>think</strong>, and repeat this cycle.</li>
  <li>The simulation stops if:
    <ul>
      <li>A philosopher <strong>dies</strong> (hasn’t eaten within <code>time_to_die</code> ms), or</li>
      <li>All philosophers have eaten <code>number_of_times_each_philosopher_must_eat</code> times (if specified).</li>
    </ul>
  </li>
</ul>

<img align="right" width="150" src="https://github.com/Abdullah-Alawad/imgs/blob/main/philo_states.png">

<h3>🧾 Log Format</h3>

<pre><code>timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X has taken a fork
timestamp_in_ms X died
</code></pre>

<ul>
  <li><code>timestamp_in_ms</code> is the time since the simulation started.</li>
  <li><code>X</code> is the philosopher’s number.</li>
</ul>

<blockquote>
  <p><strong>ℹ️ NOTE:</strong><br>
  All log messages must be <strong>printed sequentially</strong> and must <strong>not overlap</strong>.<br>
  The <code>death</code> message must be printed within <strong>10 milliseconds</strong> of the philosopher's death.</p>
</blockquote>

<h3>⚙️ How It Works</h3>

<ul>
  <li>Each philosopher is implemented as a <strong>separate thread</strong>.</li>
  <li>
  A <strong>Monitor</strong> thread is created for two reasons:
  <ul>
    <li>To detect if any philosopher has died.</li>
    <li>To check if all philosophers have eaten the required number of times (if specified).</li>
  </ul>
</li>
  <li><strong>Forks</strong> are implemented using <code>mutexes</code> to ensure exclusive access.</li>
  <li>All access to shared data is protected to avoid <strong>data races</strong>.</li>
  <li>Time is managed using <code>gettimeofday</code>.</li>
  <li>A special sleeping function using <code>usleep</code> function is coded: <code>custom_sleep</code> for accurate sleeping times without delays</li>
</ul>

<p align="center">
  <img width="600" src="https://github.com/Abdullah-Alawad/imgs/blob/main/philo1.png">
</p>
<p align="center"><sub><em>Philosopher dies in 400ms due to starvation</em></sub></p>



<p align="center">
  <img width="600" src="https://github.com/Abdullah-Alawad/imgs/blob/main/philo2.png">
</p>
<p align="center"><sub><em>After all philosophers ate at least 3 times, the simulation stops…</em></sub></p>

<h3>✅ And That’s it — May your philosophers eat well and live long!</h3>
