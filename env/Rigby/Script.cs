using System;


namespace Rigby {
	public class Script : Component {

		public virtual void Update(float delta) {
			Console.WriteLine("update " + delta);
		}
	}
}