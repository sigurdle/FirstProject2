struct ExampleBase
{
 struct Library         exb_LibNode;
 SEGLISTPTR             exb_SegList;
 struct ExecBase       *exb_SysBase;
 struct IntuitionBase  *exb_IntuitionBase;
 struct GfxBase        *exb_GfxBase;
};
