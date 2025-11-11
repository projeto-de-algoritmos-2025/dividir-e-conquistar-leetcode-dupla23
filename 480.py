from typing import List

def median_of_medians(arr, k):
    if len(arr) <= 5:
        return sorted(arr)[k]
    
    sublists = [arr[j:j+5] for j in range(0, len(arr), 5)]
    medians = [sorted(sublist)[len(sublist)//2] for sublist in sublists]

    pivot = median_of_medians(medians, len(medians)//2)

    lows = [el for el in arr if el < pivot]
    highs = [el for el in arr if el > pivot]
    pivots = [el for el in arr if el == pivot]

    if k < len(lows):
        return median_of_medians(lows, k)
    elif k < len(lows) + len(pivots):
        return pivot
    else:
        return median_of_medians(highs, k - len(lows) - len(pivots))

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        n = len(nums)
        result = []

        for i in range(n - k + 1):
            window = nums[i:i+k]
            # índice da mediana
            if k % 2 == 1:
                median = float(median_of_medians(window, k//2))
            else:
                left = median_of_medians(window, k//2 - 1)
                right = median_of_medians(window, k//2)
                median = (left + right) / 2
            result.append(median)

        return result

nums = [1, 3, -1, -3, 5, 3, 6, 7]
k = 3
print(Solution().medianSlidingWindow(nums, k))
