using System;
using System.Diagnostics;
using System.Reflection;


namespace Rigby {
	public class Engine {

	 	private static void Main(string[] args) {

		    Console.WriteLine("args: " + args.Length);
		    Array.ForEach(args, arg => 
		    	Console.WriteLine("arg: [{0}]", arg));

		    var e = new Engine();
		    e.Run();
		}

		private Level currentLevel;

		private void Run() {

		    var window = new Window();
		    window.Create();

		    var level_type = Type.GetType("Demo.Levels.IntroLevel, Demo");
		    Console.WriteLine("type: [{0}]", level_type);

		   	currentLevel = Activator.CreateInstance(level_type) as Level;
		   	currentLevel.Load();

		    var sw = Stopwatch.StartNew();

		    while (true) {

		    	long millis = sw.ElapsedMilliseconds;

		    	if (millis < 1)
		    		continue;

		    	float delta = millis / 1000.0f;

		    	window.ConsumeInput();

		    	currentLevel.UpdateScripts(delta);

		    	sw.Restart();
		    }

		    window.Destroy();
		}

		private static Level XcurrentLevel;

		public static void SetCurrentLevel(Level level) {
			XcurrentLevel = level;
		}

		public static void UpdateScripts(float delta) {
			//Console.WriteLine ("Update " + delta);
			XcurrentLevel.UpdateScripts(delta);
		}

		public static void Main () {
			Console.WriteLine ("Hello Mono World");
		}
	}
}