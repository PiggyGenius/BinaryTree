# BinaryTree

éléments 	E = e0, ..., en-1
probas 		P = p0, ..., pn-1


v.1
	c(E) = min_eidansE{ (c({ej < ei})*somme_ej + c({ek > ei})*somme_ek )/2 + 1 }

v.2
	P = 1 au début.
	c(E,P) = min_eidansE{ p_i+(c({e_j < e_i},P+1)*P + c({e_k > e_i},P+1)*P ) }
	C(e) = p_e

v.3
	c(E) = min_eidansE{ pi + (c(ej < ei)+1)*somme_pj + (c(ek > ei)+1)*somme_pk }
