let _ = print "Please enter the number of assignmnets: " in
let assignNum= readInt in

fun weights with count, assignNum, list =
if (count < assignNum) then
(let _ = print "Please enter a weight (value must be within 0 and 100 inclusive) :" in
let weight = readInt in

if (weight>100)|(weight<0) then (weights count assignNum list)
else
let l1 = weight@list in
(weights count+1 assignNum l1))

else

fun weightSum with list = 
if isNil then 0 else (weightSum #list)+!list
in
if (weightSuml1) <> 100 then print "Weights do not sum up to 100, try again." else 
