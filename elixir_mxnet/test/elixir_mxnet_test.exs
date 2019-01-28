defmodule ElixirMxnetTest do
  use ExUnit.Case
  doctest ElixirMxnet

  test "Adds numbers" do
    {:ok, data} = ElixirMxnet.init()
    assert ElixirMxnet.add(data, 1) == 101
    assert ElixirMxnet.add(data, 1) == 102
    assert ElixirMxnet.add(data, 1) == 103
  end
end
