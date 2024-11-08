QT       += core gui network widgets sql concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 -lrelease

QMAKE_LFLAGS += -static-libgcc -static-libstdc++ -static


SOURCES += \
    ElementEngine/config.cpp \
    ElementEngine/data.cpp \
    ElementEngine/elementseditor.cpp \
    GNET/octetsstream.cpp \
    dlgaddcash.cpp \
    dlgaddons.cpp \
    dlgamuleteditor.cpp \
    dlgarmoreditor.cpp \
    dlgclassmask.cpp \
    dlgcombobox.cpp \
    dlgcontasonline.cpp \
    dlgcooldowneditor.cpp \
    dlgcountrydataeditor.cpp \
    dlgextrapropeditor.cpp \
    dlgfactiondetail.cpp \
    dlgflyswordeditor.cpp \
    dlgforcedataeditor.cpp \
    dlgitemeditor.cpp \
    dlgkingdataeditor.cpp \
    dlgmanagment.cpp \
    dlgmeridiandata.cpp \
    dlgpetcorral.cpp \
    dlgpropertyeditor.cpp \
    dlgqihunessenceeditor.cpp \
    dlgrealmdataeditor.cpp \
    dlgreincarnationdataeditor.cpp \
    dlgsearchessence.cpp \
    dlgsendmail.cpp \
    dlgskillbyclass.cpp \
    dlgskills.cpp \
    dlgteste.cpp \
    dlgtesteoctetes.cpp \
    dlgtitledataeditor.cpp \
    dlgweaponeditor.cpp \
    createaccount.cpp \
    gmprivileges.cpp \
    instances.cpp \
    main.cpp \
    mainwindow.cpp \
    playereditor.cpp \
    pwadmin.cpp \
    teste.cpp

HEADERS += \
    Protocols/SysSendMail.h \
    ServerConnection.h \
    Structs/addons.h \
    PCKEngine/PCKEngine.h \
    PCKEngine/PCKFileEntry.h \
    PCKEngine/PCKKey.h \
    PCKEngine/PCKStream.h \
    PCKEngine/PCKZlib.h \
    ElementEngine/config.h \
    ElementEngine/data.h \
    ElementEngine/elementseditor.h \
    ElementEngine/elist.h \
    ElementEngine/elistcollection.h \
    ElementEngine/elistconversation.h \
    ElementEngine/option.h \
    ElementEngine/talk_proc.h \
    ElementEngine/window.h \
    GNET/octets.h \
    GNET/octetsstream.h \
    Protocols/FMemberInfo.h \
    Protocols/GFactionAliance.h \
    Protocols/GFactionDetail.h \
    Protocols/GMPlayerInfo.h \
    Protocols/GPetCorral.h \
    Protocols/GRoleBase.h \
    Protocols/GRoleDetail.h \
    Protocols/GRoleEquipment.h \
    Protocols/GRoleForbid.h \
    Protocols/GRoleInventory.h \
    Protocols/GRolePocket.h \
    Protocols/GRoleStatus.h \
    Protocols/GRoleStorehouse.h \
    Protocols/GRoleTask.h \
    Protocols/GShopLog.h \
    Protocols/GUserStorehouse.h \
    Protocols/GetConsumeInfo.h \
    Protocols/chatbroadcast.h \
    Protocols/dbautolock.h \
    Protocols/debugaddcash.h \
    Protocols/getuserroles.h \
    Protocols/gmsetgameattri.h \
    Protocols/groledata.h \
    Protocols/intoctets.h \
    Structs/fixedmsg.h \
    Structs/item.h \
    Structs/map.h \
    Structs/skill.h \
    Worker.h \
    Workers.h \
    dlgaddcash.h \
    dlgaddons.h \
    dlgamuleteditor.h \
    dlgarmoreditor.h \
    dlgclassmask.h \
    dlgcombobox.h \
    dlgcontasonline.h \
    dlgcooldowneditor.h \
    dlgcountrydataeditor.h \
    dlgextrapropeditor.h \
    dlgfactiondetail.h \
    dlgflyswordeditor.h \
    dlgforcedataeditor.h \
    dlgitemeditor.h \
    dlgkingdataeditor.h \
    dlgmanagment.h \
    dlgmeridiandata.h \
    dlgpetcorral.h \
    dlgpropertyeditor.h \
    dlgqihunessenceeditor.h \
    dlgrealmdataeditor.h \
    dlgreincarnationdataeditor.h \
    dlgsearchessence.h \
    dlgsendmail.h \
    dlgskillbyclass.h \
    dlgskills.h \
    dlgteste.h \
    dlgtesteoctetes.h \
    dlgtitledataeditor.h \
    dlgweaponeditor.h \
    connection.h \
    createaccount.h \
    game_defs.h \
    gmprivileges.h \
    instances.h \
    mainwindow.h \
    playereditor.h \
    pwadmin.h \
    server_defs.h \
    teste.h \
    utils.h

FORMS += \
    dlgaddcash.ui \
    dlgaddons.ui \
    dlgamuleteditor.ui \
    dlgarmoreditor.ui \
    dlgclassmask.ui \
    dlgcombobox.ui \
    dlgcontasonline.ui \
    dlgcooldowneditor.ui \
    dlgcountrydataeditor.ui \
    dlgextrapropeditor.ui \
    dlgfactiondetail.ui \
    dlgflyswordeditor.ui \
    dlgforcedataeditor.ui \
    dlgitemeditor.ui \
    dlgkingdataeditor.ui \
    dlgmanagment.ui \
    dlgmeridiandata.ui \
    dlgpetcorral.ui \
    dlgpropertyeditor.ui \
    dlgqihunessenceeditor.ui \
    dlgrealmdataeditor.ui \
    dlgreincarnationdataeditor.ui \
    dlgsearchessence.ui \
    dlgsendmail.ui \
    dlgskillbyclass.ui \
    dlgskills.ui \
    dlgteste.ui \
    dlgtesteoctetes.ui \
    dlgtitledataeditor.ui \
    dlgweaponeditor.ui \
    createaccount.ui \
    gmprivileges.ui \
    instances.ui \
    mainwindow.ui \
    playereditor.ui \
    pwadmin.ui \
    teste.ui

LIBS += -lz

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
