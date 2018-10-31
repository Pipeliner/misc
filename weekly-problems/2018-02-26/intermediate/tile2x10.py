	#!/usr/bin/env py

	def countWays(top, bottom):
		assert(top >= bottom)
		assert(top >= 0)
		assert(bottom >= 0)

		assert(top == bottom or top == bottom + 1)

		answer = -1

		if top == bottom == 0:
			answer = 1

		elif top == bottom:
			if top == 1:
				answer =  2
			else:
				answer =  2 * countWays(top - 1, bottom - 1) + 2 * countWays(top - 1, bottom - 2) + countWays(top - 2, bottom - 2)

		else:
			if top == 1:
				answer =  1
			elif top == 2:
				answer =  3
			else:
				answer = countWays(top - 1, bottom) + countWays(top - 1, bottom - 1)

		#print("{} {} -> {}".format(top, bottom, answer))
		return answer

	print(countWays(10, 10))