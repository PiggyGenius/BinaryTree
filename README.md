# BinaryTree

éléments 	E = e0, ..., en-1
probas 		P = p0, ..., pn-1


c = nb de comparaisons moyens optimal
	c(E) = min_eidansE{ (c(ej < ei)+1)*somme_pj + (c(ek > ei)+1)*somme_pk + pi }
