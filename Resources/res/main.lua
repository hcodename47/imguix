
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

    imgui.begin("Toolbar", isToolbarOpened, {imgui.ImGuiWindowFlags_MenuBar})
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

        if imgui.imageButton("res/1.png") then print("image button click 1") end
        imgui.sameLine() if imgui.imageButton("res/1.png") then print("image button click 2") end
        imgui.sameLine() if imgui.imageButton("res/1.png") then print("image button click 3") end
        imgui.sameLine() if imgui.imageButton("res/1.png") then print("image button click 4") end
        imgui.sameLine() if imgui.imageButton("res/1.png") then print("image button click 5") end

        if imgui.imageButton("#CoinSpin01.png") then print("CoinSpin01 1") end
        imgui.sameLine() if imgui.imageButton("#CoinSpin01.png") then print("CoinSpin01 2") end
        imgui.sameLine() if imgui.imageButton("#AddCoinButton.png", 30, 30) then print("AddCoinButton") end

    imgui.endToLua()
end
