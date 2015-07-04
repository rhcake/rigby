using System;
using System.Diagnostics;
using System.Reflection;
using Rigby.Math;


namespace Rigby {
	public class Engine {

	 	private static void Main(string[] args) {

		    Console.WriteLine("args: " + args.Length);
		    Array.ForEach(args, arg => 
		    	Console.WriteLine("arg: [{0}]", arg));

		    var e = new Engine();
		    e.Run();
		}

		public Level CurrentLevel {
			get;
			private set;
		}

		private Renderer renderer;

		private void Run() {

			var am = new AssetManager();
			var mesh = am.LoadMesh("suzanne.obj");

		    var window = new Window();
		    window.Create();

		    renderer = new Renderer(this);

		    var level_type = Type.GetType("Demo.Levels.IntroLevel, Demo");
		    Console.WriteLine("type: [{0}]", level_type);

		   	CurrentLevel = Activator.CreateInstance(level_type) as Level;
		   	CurrentLevel.Load();
		   	CurrentLevel.camera = new Camera();
		   	CurrentLevel.camera.backgroundColor = 
		   		new Vector3f(0.2f, 0.3f, 0.4f);

		    var sw = Stopwatch.StartNew();

		    while (true) {

		    	long millis = sw.ElapsedMilliseconds;

		    	if (millis < 1)
		    		continue;

		    	float delta = millis / 1000.0f;

		    	window.ConsumeInput();

		    	CurrentLevel.UpdateScripts(delta);

		    	// TODO
		    	renderer.render();

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