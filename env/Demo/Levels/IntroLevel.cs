using Rigby;
using System;
using Demo.Actors;
using Demo.Scripts;

namespace Demo.Levels {

	public class IntroLevel : Level {

		public IntroLevel() {
			Console.WriteLine("IntroLevel ctor");
		}

		public override void Load() {
			Console.WriteLine("Loading intro level");

			var script = new MyScript();
			var actor = new MyActor();
			actor.AddComponent(script);
			actor.AddComponent(new Transform());
			AddActor(actor);
		}
	}
}