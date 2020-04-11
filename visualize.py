from mayavi import mlab
import numpy as np

def plot_box(corner, length):
    mlab.plot3d([corner, corner+length], [0, 0], [0, 0], color=black, tube_radius=1.5)
    mlab.plot3d([corner, corner], [0, length], [0, 0], color=black, tube_radius=1.5)
    mlab.plot3d([corner, corner+length], [length, length], [0, 0], color=black, tube_radius=1.5)
    mlab.plot3d([corner+length, corner+length], [0, length], [0, 0], color=black, tube_radius=1.5)
    mlab.plot3d([corner, corner], [0, 0], [0, length], color=black, tube_radius=1.5)
    mlab.plot3d([corner, corner+length], [0, 0], [length, length], color=black, tube_radius=1.5)
    mlab.plot3d([corner, corner], [0, length], [length, length], color=black, tube_radius=1.5)
    mlab.plot3d([corner, corner], [length, length], [0, length], color=black, tube_radius=1.5)
    mlab.plot3d([corner+length, corner+length], [0, 0], [0, length], color=black, tube_radius=1.5)
    mlab.plot3d([corner+length, corner+length], [length, length], [0, length],
                color=black, tube_radius=1.5)
    mlab.plot3d([corner+length, corner+length], [0, length], [length, length],
                color=black, tube_radius=1.5)
    mlab.plot3d([corner, corner+length], [length, length], [length, length],
                color=black, tube_radius=1.5)


def plot_ball(corner, position, size):
    mlab.points3d(corner+position[0], position[1], position[2], size, resolution=60, scale_factor=2)


if __name__ == "__main__":
    black = (0, 0, 0)
    white = (1., 1., 1.)
    mlab.figure(fgcolor=(0., 0., 0.), bgcolor=(1., 1., 1.))
    f = open('output/output_1.txt', 'r')
    length = int(f.readline())
    number = int(f.readline())
    for i in range(number):
        plot_box((50+length)*i, length)

    for line in f:
        line = str.split(line)
        plot_ball((int(line[0])-1) * (50+length), (float(line[2]), float(line[3]),
                                              float(line[4])), float(line[1]))

    f.close()
    mlab.show()

