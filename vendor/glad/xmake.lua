--package("glad")
--  set_description("glad")
--  on_fetch(function (package)
--    local result = {}
--    --result.links = "glad"
--    result.includedirs = package:installdir("includedirs")
--    return result
--  end)
add_rules("mode.debug", "mode.release")
target("glad")
    add_includedirs("include")
    add_files("src/*.cpp")