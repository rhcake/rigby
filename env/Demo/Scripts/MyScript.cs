using Rigby;
using System;


namespace Demo.Scripts {

	public class MyScript : Script {

		private float total = 0.0f;
		private int frames = 0;
		private float limit = 1.0f;

		public override void Update(float delta) {

			total += delta;
			frames += 1;

			if (total > limit) {
				
				int fps = (int)(frames / limit);
				total = 0.0f;
				frames = 0;

				new Window().SetTitle("fps " + fps);

				var pos = actor.transform.position;
				Console.WriteLine(pos);
			}
		}
	}
}