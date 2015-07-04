


namespace Rigby {

	public class Renderer {

		private Engine engine;

		public Renderer(Engine engine) {
			this.engine = engine;
		}

		public void render() {

			var camera = engine.CurrentLevel.camera;
		}
	}
}