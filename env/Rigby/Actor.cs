using System.Collections.Generic;


namespace Rigby {

	public class Actor {

		private List<Component> components = new List<Component>();
		private List<Script> scripts = new List<Script>();

		public Transform transform {
			get;
			private set;
		}

		public void AddComponent(Component comp) {

			comp.actor = this;
			
			components.Add(comp);

			if (comp is Script) {
				scripts.Add(comp as Script);
			} else if (comp is Transform) {
				transform = comp as Transform;
			}
		}

		public void UpdateScripts(float delta) {

			scripts.ForEach(script =>
				script.Update(delta));
		}
	}
}