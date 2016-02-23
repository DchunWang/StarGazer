import QtQuick 2.2

Rectangle{
    width: 400;
    height: 300;
    Item{
        id: gradientGroup;
        Rectangle{
            x: 20;
            y: 20;
            width: 120;
            height: 120;
            gradient: Gradient{
                GradientStop { position: 0.0; color: "#202020";}
                GradientStop { position: 1.0; color: "#A0A0A0";}
            }
        }

        Rectangle{
            x: 160;
            y: 20;
            width: 120;
            height: 120;
            rotation: 90;
            gradient: Gradient{
                GradientStop { position: 0.0; color: "#202020";}
                GradientStop { position: 1.0; color: "#A0A0A0";}
            }
        }
    }

    Component.onCompleted: {
        console.log("visible children:", gradientGroup.visibleChildren.length);
        console.log("children:", gradientGroup.children.length);
        for(var i = 0; i < gradientGroup.children.lenght; ++i)
        {
            console.log("child", i, "x=", gradientGroup.childrent[i].x);
        }
    }
}

