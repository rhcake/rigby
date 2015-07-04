using System;


namespace Rigby.Components {
	public class Script : Component {

		public virtual void Update(float delta) {
			Console.WriteLine("update " + delta);
		}
	}
}