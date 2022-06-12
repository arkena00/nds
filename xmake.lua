
target("lib_nds")
    set_kind("headeronly")
    add_includedirs("include", {interface = true})
    add_files("source/**/*.cpp")