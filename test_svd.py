import numpy as np
import svd_cpp
import sys

def test_svd():
    print("Test SVD pybind implementation")


    print("Test 1: 2x2 matrix")
    matrix1 = [[1.0, 2.0], [3.0, 4.0]]
    print("Input matrix:")
    print(np.array(matrix1))
    
    # My svd
    U_cpp, S_cpp, Vt_cpp = svd_cpp.svd(matrix1)
    # Numpy svd
    U_np, S_np, Vt_np = np.linalg.svd(matrix1)
    
    print("C++ SVD results:")
    print("U:", np.array(U_cpp))
    print("S:", np.array(S_cpp))
    print("Vt:", np.array(Vt_cpp))
    
    print("NumPy SVD results:")
    print("U:", U_np)
    print("S:", S_np)
    print("Vt:", Vt_np)
    
    # Reconstruct matrix
    reconstructed_cpp = U_cpp @ np.diag(S_cpp) @ Vt_cpp
    reconstructed_np = U_np @ np.diag(S_np) @ Vt_np
    
    error1 = np.linalg.norm(np.array(matrix1) - reconstructed_cpp)
    error_np1 = np.linalg.norm(np.array(matrix1) - reconstructed_np)

    print("\nReconstruction error (C++):", error1)
    print("Reconstruction error (NumPy):", error_np1)
    

    print("\n Test 2: 3x2 matrix")
    matrix2 = [[3.1, 4.5], [1.3, 2.8], [7.7, 6.6]]
    print("Input matrix:")
    print(np.array(matrix2))
    
    # My svd
    U_cpp2, S_cpp2, Vt_cpp2 = svd_cpp.svd(matrix2)
    # Numpy svd
    U_np2, S_np2, Vt_np2 = np.linalg.svd(matrix2, full_matrices=False)
    
    reconstructed_cpp2 = U_cpp2 @ np.diag(S_cpp2) @ Vt_cpp2
    reconstructed_np2 = U_np2 @ np.diag(S_np2) @ Vt_np2

    error2 = np.linalg.norm(np.array(matrix2) - reconstructed_cpp2)
    error_np2 = np.linalg.norm(np.array(matrix2) - reconstructed_np2)
    
    print("Reconstruction error (C++):", error2)
    print("Reconstruction error (Numpy):", error_np2)
    
    
    print("\nTest 3: random 4x3 matrix")
    np.random.seed(42)
    matrix3 = np.random.rand(4, 3).tolist()
    
    U_cpp3, S_cpp3, Vt_cpp3 = svd_cpp.svd(matrix3)
    U_np3, S_np3, Vt_np3 = np.linalg.svd(matrix3, full_matrices=False)

    reconstructed_cpp3 = U_cpp3 @ np.diag(S_cpp3) @ Vt_cpp3
    reconstructed_np3 = U_np3 @ np.diag(S_np3) @ Vt_np3

    error3 = np.linalg.norm(np.array(matrix3) - reconstructed_cpp3)
    error_np3 = np.linalg.norm(np.array(matrix3) - reconstructed_np3)
    
    print("Reconstruction error (C++):", error3)
    print("Reconstruction error (Numpy):", error_np3)

    
    # Check if all tests passed
    if error1 < 1e-5 and error2 < 1e-5 and error3 < 1e-5:
        print("All tests passed!")
        return True
    else:
        print("Some tests failed!")
        return False

if __name__ == "__main__":
    success = test_svd()
    sys.exit(0 if success else 1)