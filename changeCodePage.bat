echo on
for %%i in ("*.dfm") do sed s/DEFAULT_CHARSET/RUSSIAN_CHARSET/ %%i >%%i1
