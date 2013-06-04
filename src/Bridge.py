xmap = [1, 2, 4, 8, 16, 32, 64, 128, 256]
matrix = []
for a_0 in range(0, 2):
	for a_1 in range(0, 2):
		for a_2 in range(0, 2):
			for a_3 in range(0, 2):
				for a_4 in range(0, 2):
					for a_5 in range(0, 2):
						for a_6 in range(0, 2):
							for a_7 in range(0, 2):
								for a_8 in range(0, 2):
									L_1 = (not a_8) and (not a_0) and a_1 and (not a_2) and a_3 and (not a_4) and (not a_5) and (not a_6) and (not a_7)
									L_2 = (not a_8) and (not a_0) and (not a_1) and (not a_2) and a_3 and (not a_4) and a_5 and (not a_6) and (not a_7)
									L_3 = (not a_8) and (not a_0) and (not a_1) and (not a_2) and (not a_3) and (not a_4) and a_5 and (not a_6) and a_7
									L_4 = (not a_8) and (not a_0) and a_1 and (not a_2) and (not a_3) and (not a_4) and (not a_5) and (not a_6) and a_7
									P_Q = L_1 or L_2 or L_3 or L_4
									P_1 = (not a_2) and (not a_6) and (a_3 or a_4 or a_5) and (a_0 or a_1 or a_7) and (not P_Q)
									P_2 = (not a_0) and (not a_4) and (a_1 or a_2 or a_3) and (a_5 or a_6 or a_7) and (not P_Q)
									P_3 = (not a_0) and (not a_6) and a_7 and (a_2 or a_3 or a_4)
									P_4 = (not a_0) and (not a_2) and a_1 and (a_4 or a_5 or a_6)
									P_5 = (not a_2) and (not a_4) and a_3 and (a_0 or a_6 or a_7)
									P_6 = (not a_4) and (not a_6) and a_5 and (a_0 or a_1 or a_2)
									G = a_8 or (P_1 or P_2 or P_3 or P_4 or P_5 or P_6)
									fuck = [a_3, a_2, a_1, a_4, a_8, a_0, a_5, a_6, a_7]
									if G == 1 and (fuck not in matrix):
										matrix.append(fuck)
print len(matrix)
