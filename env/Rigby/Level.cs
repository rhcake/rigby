using System.Collections.Generic;


namespace Rigby {

	public class Level {

		public virtual void Load() {}

		private List<Actor> actors = new List<Actor>();

		public void UpdateScripts(float delta) {

			actors.ForEach(a =>
				a.UpdateScripts(delta));
		}

		protected void AddActor(Actor actor) {
			actors.Add(actor);
		}
	}
}