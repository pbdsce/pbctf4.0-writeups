import cv2
import numpy as np

# --- Re-implementation of xorshift32 PRNG ---
def xorshift32(state):
    state ^= (state << 13) & 0xFFFFFFFF
    state ^= (state >> 17) & 0xFFFFFFFF
    state ^= (state << 5) & 0xFFFFFFFF
    return state & 0xFFFFFFFF

def decrypt_video(input_path, output_path, seed):
    cap = cv2.VideoCapture(input_path)
    if not cap.isOpened():
        print("Failed to open input video.")
        return

    width  = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fps    = int(cap.get(cv2.CAP_PROP_FPS))

    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    out = cv2.VideoWriter(output_path, fourcc, fps, (width, height))

    prng_state = seed

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        decrypted = frame.copy()

        for y in range(decrypted.shape[0]):
            for x in range(decrypted.shape[1]):
                for c in range(3):  # BGR
                    prng_state = xorshift32(prng_state)
                    key = prng_state & 0xFF
                    decrypted[y, x, c] ^= key

        out.write(decrypted)

    cap.release()
    out.release()
    print(f"Decryption complete: {output_path}")

# === Usage ===
if __name__ == "__main__":
    encrypted_video = input("Encrypted video: ")
    output_video = input("Output path: ")
    seed = 0xDEADBEEF  # They should extract this from the binary

    decrypt_video(encrypted_video, output_video, seed)
