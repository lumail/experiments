--
-- This script times how long it takes to parse the two cache-files
-- we have got.
--
-- If you don't have the cache-files run `make-cache` first.
--


--
-- The results go here
--
local ini_results = {}
local rec_results = {}

function parse_ini()
   for line in io.lines("cache.ini") do
      -- greedy match on key-name.
      key, val = line:match("^(.*)=([^=]+)$")
      if ( key and val ) then
         ini_results[key] = val
      end
   end
end

function CacheEntry( t )
   rec_results[t.key] = t.val
end
function parse_rec()
   dofile( "cache.rec" )
end


function write_cache()
   local hand = io.open("cache.out.rec","w")

   -- Now the key/values from our cache.
   for key,val in pairs(rec_results) do

      hand:write( "CacheEntry{ key = \"" .. key .. "\", val=\"" .. val .. "\"}\n" );
   end
   hand:close()
end


--
-- Run the first test.
--
local start = os.time()
parse_ini()
local send   = os.time()
print( "Time to parse `cache.ini` was " .. ( send - start ) .. " seconds" )

--
-- Run the second test
--
local start = os.time()
parse_rec()
local send = os.time()
print( "Time to parse `cache.rec` was " .. ( send - start ) .. " seconds" )

--
-- Sanity-check.
--
-- Are the two files identical?
--
assert( #ini_results == #rec_results )


--
-- How long does it take to write our our cache?
--
local start = os.time()
write_cache()
local send = os.time()
print( "Time to write out the cache was " .. ( send - start ) .. " seconds" )
