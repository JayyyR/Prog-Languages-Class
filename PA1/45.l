 fun sort with list, newList =
if isNil list then
  newList
else
  let grade = !list in
  let tl = #list in
  if isNil #tl then
    let lastgrade = grade@tl in
    (insert lastgrade newList)
  else
    let sortList = (insert grade newList) in
    (sort tl sortList)
