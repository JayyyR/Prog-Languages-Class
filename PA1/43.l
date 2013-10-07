let reverse = lambda list .
    let _reverse = lambda list, reversed .
        if (isVoid list) then reversed
        else (_reverse #list !list@reversed) in
    (_reverse list Void) in
(reverse 123@0001@2301@678@"ahoj!")
