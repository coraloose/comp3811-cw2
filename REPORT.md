# Coursework 2 Report

## Task 1.1 – Matrix/vector functions

### Implemented functionality
- Added 4×4 matrix multiplication and matrix–vector multiplication operators to support transforming matrices and points/vectors directly with `Mat44f`.
- Provided rotation matrix factories `make_rotation_x`, `make_rotation_y`, and `make_rotation_z` that build the conventional right-handed rotation matrices using cosine/sine around each principal axis.
- Added `make_translation` for embedding 3D offsets into homogeneous coordinates.
- Implemented `make_perspective_projection` to generate a standard perspective projection matrix parameterised by field of view, aspect ratio, and near/far planes.

### Tests
- **Perspective projection** (`vmlib-test/projection.cpp`): verifies the projection matrix entries for a 60° FOV, 1280×720 viewport setup and for a square 90° FOV case to confirm depth and aspect computations.
- **Rotations** (`vmlib-test/rotation.cpp`): applies quarter-turn rotations around each principal axis to sample vectors to confirm axis-specific cosine/sine placement and handedness.
- **Translation** (`vmlib-test/translation.cpp`): checks matrix layout (last column offsets and homogeneous row) and validates transforming a point by the translation matrix.
- **Multiplication** (`vmlib-test/mult.cpp`): exercises matrix–matrix multiplication against a hand-computed product and matrix–vector multiplication against an expected transformed vector.
