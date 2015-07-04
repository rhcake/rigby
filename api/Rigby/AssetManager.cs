using Rigby.Graphics;


namespace Rigby {
	
	public class AssetManager {

		private AssetLoader al = new AssetLoader();

		public Mesh LoadMesh(string name) {

			var raw = al.LoadAsset(name);

			return null;
		}
	}
}
