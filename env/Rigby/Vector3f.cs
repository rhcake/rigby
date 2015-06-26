


namespace Rigby {
	public class Vector3f {
		public float x, y, z;
		public Vector3f(float x, float y, float z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}
		public Vector3f() : this(0.0f, 0.0f, 0.0f) {}
		public override string ToString() {
			return x + ", " + y + ", " + z;
		}
	}
}