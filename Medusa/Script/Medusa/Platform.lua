
function trynumber(value, base)
    return tonumber(value, base) or 0
end

function tryint(value)
    return math.round(trynumber(value))
end

function trybool(value)
    return (value ~= nil and value ~= false)
end

function trytable(value)
    if type(value) ~= "table" then value = {} end
    return value
end
