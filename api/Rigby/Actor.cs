using System.Collections.Generic;
using Rigby.Components;


namespace Rigby {

	public class Actor {

		private List<Component> components = new List<Component>();
		private List<Script> scripts = new List<Script>();

		public void AddComponent(Component comp) {

			comp.actor = this;
			
			components.Add(comp);

			if (comp is Script) {
				scripts.Add(comp as Script);
			} 
		}

		public void UpdateScripts(float delta) {

			scripts.ForEach(script =>
				script.Update(delta));
		}
	}
}