
target("nds")
    set_kind("static")
    add_includedirs("include", { public = true })
    add_files("source/**/*.cpp")
    add_headerfiles("include/(**.hpp)", "include/(**.tpp)")