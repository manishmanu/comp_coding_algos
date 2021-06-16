
def preprocess(pattern):
    kmp_arr = [0]*len(pattern)
    j = 0
    for i in range(1, len(pattern)):
        while True:
            if pattern[j] == pattern[i]:
                kmp_arr[i] = j + 1
                j += 1
                break
            else:
                if j == 0:
                    kmp_arr[i] = j
                    break
                else:
                    j = kmp_arr[j-1]
    return kmp_arr


def match(text, pattern, kmp_arr):
    match_indices = []
    p = 0
    for t in range(0, len(text)):
        while True:
            if text[t] == pattern[p]:
                if p == (len(pattern) - 1):
                    match_indices.append(t-p)
                    p = kmp_arr[p]
                else:
                    p += 1
                break
            else:
                if p == 0:
                    break
                else:
                    p = kmp_arr[p-1]
    return match_indices


def main():
    text = "abcxabcdabxabcdabcdabcyabcabcdabcyy"
    pattern = "abcdabcy"
    kmp_array = preprocess(pattern)
    print('kmp preprocessed array for ', pattern, ':', kmp_array)
    matches = match(text, pattern, kmp_array)
    print('matched indices : ', matches)


if (__name__ == "__main__"):
    main()
