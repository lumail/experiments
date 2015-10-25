
t = Sample.new()
print( "Lua calls the method implemented in C++ " .. t:one() )
print( "Lua calls the method implemented in C++ " .. t:two() )

-- Now define a method
function Sample:three(self)
   print ("OK" )
   return "C++ calls the method implemented in Lua"
end
