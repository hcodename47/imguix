print('hellllo from lua')

local function createDefaultWindow()
    ImGui.Separator()
    ImGui.Text('Hello from Lua')
end

local function createToolWindow()
    ImGui.Begin('Lua Window')
    if ImGui.Button('Lua Button') then
        print('click Lua Button', os.time())
        cxxfun()
    end
    ImGui.End()
end

function ImGuiRenderer()

    createDefaultWindow()
    createToolWindow()
end

