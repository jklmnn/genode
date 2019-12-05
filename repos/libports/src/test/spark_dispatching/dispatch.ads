
package Dispatch
is

   procedure Run (Result : out Integer) with
      Export,
      Convention    => C,
      External_Name => "run_dispatch";

end Dispatch;
