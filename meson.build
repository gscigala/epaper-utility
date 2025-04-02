project('epaper-utility', ['c'], default_options : ['c_std=c17'])

include_dirs = include_directories(
    'lib/e-Paper/E-paper_Separate_Program/2in15_e-Paper_G/RaspberryPi_JetsonNano/c/lib/Config',
    'lib/e-Paper/E-paper_Separate_Program/2in15_e-Paper_G/RaspberryPi_JetsonNano/c/lib/e-Paper',
    'lib/e-Paper/E-paper_Separate_Program/2in15_e-Paper_G/RaspberryPi_JetsonNano/c/lib/GUI',
)

src_files = files('src/main.c',
                  'lib/e-Paper/E-paper_Separate_Program/2in15_e-Paper_G/RaspberryPi_JetsonNano/c/lib/Config/DEV_Config.c',
                  'lib/e-Paper/E-paper_Separate_Program/2in15_e-Paper_G/RaspberryPi_JetsonNano/c/lib/e-Paper/EPD_2in15g.c',
                  'lib/e-Paper/E-paper_Separate_Program/2in15_e-Paper_G/RaspberryPi_JetsonNano/c/lib/GUI/GUI_Paint.c',
                  'lib/e-Paper/E-paper_Separate_Program/2in15_e-Paper_G/RaspberryPi_JetsonNano/c/lib/GUI/GUI_BMPfile.c',
)

executable('epaper-utility',
           src_files,
           include_directories: include_dirs,
           link_args: ['-Wl,--gc-sections','-lbcm2835','-lm'],
           install: true,
           install_dir: '/usr/bin'
)

install_data('res/splash.bmp', install_dir: '/etc/epaper')
