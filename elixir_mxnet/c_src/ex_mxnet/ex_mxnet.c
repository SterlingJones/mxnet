#include <stdlib.h>
#include <erl_nif.h>
#include <assert.h>
#include "ex_mxnet.h"

static void rt_dtor(ErlNifEnv *env, void *obj) {
    resource_data_t *rd = (resource_data_t *)obj;
    (void)env;  // not used.
    (void)rd;   // not used.
    enif_fprintf(stderr, "rt_dtor called\r\n");
}

static int load(ErlNifEnv* env, void** priv, ERL_NIF_TERM info) {
    (void)info; // not used.
    priv_data_t* data = enif_alloc(sizeof(priv_data_t));
    if (data == NULL) return 1;

    data->atom_ok = enif_make_atom(env, "ok");
    data->atom_undefined = enif_make_atom(env, "undefined");
    data->atom_error = enif_make_atom(env, "error");
    data->atom_nil = enif_make_atom(env, "nil");
    data->atom_true = enif_make_atom(env, "true");
    data->atom_false = enif_make_atom(env, "false");
    *priv = (void*)data;
    resource_type = enif_open_resource_type(env, "Elixir.ExMXNet", "ex_mxnet_nif", &rt_dtor, ERL_NIF_RT_CREATE, NULL);
    return !resource_type;
}

static int reload(ErlNifEnv* env, void** priv, ERL_NIF_TERM info) {
    (void)env;  // not used.
    (void)priv; // not used.
    (void)info; // not used.
    return 0;
}

static int upgrade(ErlNifEnv* env, void** priv, void** old_priv, ERL_NIF_TERM info) {
    (void)env;  // not used.
    (void)priv; // not used.
    (void)old_priv; // not used.
    return load(env, priv, info);
}

static void unload(ErlNifEnv* env, void* priv) {
    (void)env;  // not used.
    (void)priv; // not used.
    enif_free(priv);
}

static ERL_NIF_TERM ex_mxnet_init(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    assert(argc == 0);
    (void)argv; // not used.
    priv_data_t* priv = enif_priv_data(env);
    resource_data_t *rd;

    ERL_NIF_TERM res;

    rd = enif_alloc_resource(resource_type, sizeof(resource_data_t));
    rd->left = 100;

    res = enif_make_resource(env, rd);
    enif_release_resource(rd);

    return enif_make_tuple2(env, priv->atom_ok, res);
}

static ERL_NIF_TERM ex_mxnet_add(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
  assert(argc == 2);
  priv_data_t* priv = enif_priv_data(env);
  (void)priv; // not used.
  resource_data_t *rd;
  int right;

  if(!enif_get_resource(env, argv[0], resource_type, (void **)&rd))
      return enif_make_badarg(env);

  if(!enif_get_int(env, argv[1], &right))
      return enif_make_badarg(env);

  rd->left = rd->left + right;
  return enif_make_int(env, rd->left);
}
