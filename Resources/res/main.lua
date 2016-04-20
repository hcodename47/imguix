
print (imgui.version)
print (imgui.ImGuiWindowFlags_NoTitleBar)

-- data

local buf = "Quick brown fox"
local float = 3
local isToolbarOpened = true

-- draw

function setup_mainmenu()
    if imgui.beginMainMenuBar() then
        if imgui.beginMenu("File") then
            imgui.endMenu()
        end

        if imgui.beginMenu("Edit") then
            if imgui.menuItem("Undo") then print("undo") end
            if imgui.menuItem("Redo") then print("redo") end
            imgui.separator()
            if imgui.menuItem("Cut") then
                print("cut")
            end
            imgui.endMenu()
        end

        imgui.endMainMenuBar()
    end
end

imgui.draw = function ()
    setup_mainmenu()

    imgui.text("[lua] Hello, World!")
    if imgui.button("[lua] OK") then
        print ("click ok")
    end

    if imgui.begin("Toolbar", isToolbarOpened, {imgui.ImGuiWindowFlags_MenuBar}) then
        if imgui.beginMenuBar() == true then
            if imgui.beginMenu("File") == true then
                imgui.menuItem("Open")
                imgui.menuItem("Save")
                imgui.endMenu()
            end
            imgui.endMenuBar()
        end

        _, buf = imgui.inputText("[lua] input", buf, 256)
        _, float = imgui.sliderFloat("[lua] float", float, 0, 8)

        if imgui.imageButton("res/1.png") then print("image button click") end
        imgui.sameLine()
        if imgui.imageButton("res/1.png") then print("image button click 2") end

        imgui.endToLua()
    end
end
